package main

import (
	"log"
	"net"
	"strconv"
	"strings"
	"sync"
)

// Сигналы клиенту от основного потока
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
	SelectItemToIdConv []uint
	History            map[uint][]string

	ChanIn  net.Conn
	ChanOut net.Conn

	IsValid bool
}

func NewClient() Client {
	var client Client
	client.History = make(map[uint][]string, 100)
	client.IsValid = true
	return client
}

func (client *Client) Process(chClient_MainThread chan any, chEventToMainThread chan int) {

	var wgForSyncFibers sync.WaitGroup
	wgForSyncFibers.Add(1)
	var wgCloseClient sync.WaitGroup
	wgCloseClient.Add(2)
	var err error
	go func() {
		defer wgCloseClient.Done()
		if client.ChanOut, err = net.Dial("tcp", "localhost:993"); err != nil {
			log.Println("Server connection error")
			panic(err)
		} else {
			defer client.ChanOut.Close()
			wgForSyncFibers.Done()
			for {

				if !client.IsValid {
					break
				}
				switch (<-chClient_MainThread).(int) {

				case ET_AUTHORIZATION:
					bufMail := (<-chClient_MainThread).(string)
					bufPassword := (<-chClient_MainThread).(string)
					bufStr := bufMail + ";" + bufPassword
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
						chClient_MainThread <- ET_AUTHORIZATION
					} else {
						client.IsValid = false
						chClient_MainThread <- ET_FAILED_AUTHORIZATION
					}

				case ET_SEND_MESSAGE:
					idConv := (<-chClient_MainThread).(int)
					bufStr := (<-chClient_MainThread).(string)
					client.Send(client.ChanOut, NewMessage(int64(idConv), int64(client.Id), MT_MESSAGE, bufStr))
					_ = client.Receive(client.ChanOut)
					client.History[uint(idConv)] = append(client.History[uint(idConv)], client.FirstName+" "+client.LastName+": "+bufStr)

				case ET_EXIT:
					client.IsValid = false
					client.Send(client.ChanOut, NewMessage(0, 0, MT_EXIT, ""))
					_ = client.Receive(client.ChanOut)

				}

			}
		}
	}()

	go func() {
		defer wgCloseClient.Done()
		wgForSyncFibers.Wait()
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
					client.SelectItemToIdConv = make([]uint, len(stringsBuf)/2)
					i := 0
					j := 0
					for i < len(stringsBuf)-1 {
						buf, _ := strconv.Atoi(stringsBuf[i])
						client.CacheConversations[uint(buf)] = stringsBuf[i+1]
						client.SelectItemToIdConv[uint(j)] = uint(buf)
						i += 2
						j++
					}
					chEventToMainThread <- UPDATE_USER_LIST
				case MT_MESSAGE:
					if _, ok := client.History[uint(m.Header.To)]; ok {
						client.History[uint(m.Header.To)] = append(client.History[uint(m.Header.To)], m.Data)
					} else {
						client.History[uint(m.Header.To)] = []string{}
						client.History[uint(m.Header.To)] = append(client.History[uint(m.Header.To)], m.Data)
					}

					chEventToMainThread <- UPDATE_MESSAGE
					chClient_MainThread <- int(m.Header.To)
				case MT_EXIT:
				}
			}
		}
	}()
	wgCloseClient.Wait()
	chClient_MainThread <- struct{}{}
	log.Println("Завершение всех потоков на клиенте")

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
