package main

import (
	"log"
	"net"
	"strconv"
	"strings"
	"sync"
)

const (
	ET_AUTHORIZATION = iota
	ET_FAILED_AUTHORIZATION
	ET_SEND_MESSAGE
	ET_EXIT
)

type Client struct {
	Id         uint
	FirstName  string
	LastName   string
	NameAvatar string

	CacheConversations map[uint]string
	SelectItemToIdConv map[uint]uint
	History            map[uint][]string

	ChanIn  net.Conn
	ChanOut net.Conn

	IsValid bool

	wg sync.WaitGroup
}

func NewClient() Client {
	var client Client
	client.History = make(map[uint][]string, 100)
	client.IsValid = true
	client.wg.Add(1)
	return client
}

func (client *Client) Process(ch chan int, ch2 chan int, ch3 chan string, wg *sync.WaitGroup, wg2 *sync.WaitGroup, chatForm *ChatForm, authorizationForm *AuthorizationForm) {

	var wgs sync.WaitGroup
	wgs.Add(1)
	var err error
	go func() {
		defer wg2.Done()
		if client.ChanOut, err = net.Dial("tcp", "localhost:993"); err != nil {
			log.Println("Server connection error")
			panic(err)
		} else {
			defer client.ChanOut.Close()
			wgs.Done()
			wg.Done()
			for {
				client.wg.Wait()
				client.wg.Add(1)
				if !client.IsValid {
					break
				}
				switch <-ch {

				case ET_AUTHORIZATION:
					bufStr := authorizationForm.EmailEntry.Text + ";" + authorizationForm.PasswordEntry.Text
					client.Send(client.ChanOut, NewMessage(0, 0, MT_AUTHORIZATION, bufStr))
					var m Message = client.Receive(client.ChanOut)
					if m.Header.Type == MT_AUTHORIZATION_SUCCESS {
						dataClient := strings.Split(m.Data, ";")
						if bufInt, err := strconv.Atoi(dataClient[0]); err != nil {

						} else {
							client.Id = uint(bufInt)
						}
						client.FirstName = dataClient[1]
						client.LastName = dataClient[2]
						client.NameAvatar = dataClient[3]
						ch <- ET_AUTHORIZATION
					} else {
						client.IsValid = false
						ch <- ET_FAILED_AUTHORIZATION
					}

				case ET_SEND_MESSAGE:
					idConv := <-ch
					bufStr := <-ch3
					client.Send(client.ChanOut, NewMessage(int64(idConv), int64(client.Id), MT_MESSAGE, bufStr))
					_ = client.Receive(client.ChanOut)
					client.History[uint(idConv)] = append(client.History[uint(idConv)], client.FirstName+" "+client.LastName+": "+bufStr)

				case ET_EXIT:
					client.IsValid = false
					client.Send(client.ChanOut, NewMessage(0, 0, MT_EXIT, ""))
					_ = client.Receive(client.ChanOut)
					client.wg.Done()

				}

				wg.Done()

			}
		}
	}()

	go func() {
		defer wg2.Done()
		wgs.Wait()
		if client.ChanIn, err = net.Dial("tcp", "localhost:993"); err != nil {
			log.Println("Server connection error")
			panic(err)
		} else {
			defer client.ChanIn.Close()
			for {
				if !client.IsValid {
					break
				}
				var m Message = client.Receive(client.ChanIn)
				switch m.Header.Type {

				case MT_UPDATE_USER_LIST:
					stringsBuf := strings.Split(m.Data, ";")
					client.CacheConversations = make(map[uint]string, 100)
					client.SelectItemToIdConv = make(map[uint]uint, 100)
					i := 0
					j := 0
					for i < len(stringsBuf)-1 {
						buf, _ := strconv.Atoi(stringsBuf[i])
						client.CacheConversations[uint(buf)] = stringsBuf[i+1]
						client.SelectItemToIdConv[uint(j)] = uint(buf)
						i += 2
						j++
					}
					ch2 <- UPDATE_USER_LIST
				case MT_MESSAGE:

					if _, ok := client.History[uint(m.Header.To)]; ok {
						client.History[uint(m.Header.To)] = append(client.History[uint(m.Header.To)], m.Data)
					} else {
						client.History[uint(m.Header.To)] = []string{}
						client.History[uint(m.Header.To)] = append(client.History[uint(m.Header.To)], m.Data)
					}
					ch2 <- UPDATE_MESSAGE
					ch <- int(m.Header.To)
				case MT_EXIT:

				}

			}
		}
	}()
	wg2.Wait()
	//wg.Done()
}

func (client *Client) Close() {

}

func (client *Client) Send(channel net.Conn, m *Message) {
	m.Header.Send(channel)
	if m.Header.Size > 0 {
		channel.Write(to866(m.Data))
	}
}

func (client *Client) Receive(channel net.Conn) Message {
	var m Message
	m.Header.Receive(channel)
	if m.Header.Size > 0 {
		buff := make([]byte, m.Header.Size)
		channel.Read(buff)
		m.Data = from866(buff)
	}
	return m
}
