package main

import (
	"bytes"
	"encoding/binary"
	"io"
	"net"
	"unsafe"

	"golang.org/x/text/encoding/charmap"
	"golang.org/x/text/transform"
)

const (
	MT_AUTHORIZATION = iota
	MT_AUTHORIZATION_FAILED
	MT_AUTHORIZATION_SUCCESS
	MT_EXIT
	MT_GETDAT
	MT_DATA
	MT_USERS
	MT_NODATA
	MT_CONFIRM
	MT_UPDATE_USER_LIST
	MT_MESSAGE
	MT_MESSAGE_ALL
	MT_GET_ID_RECIPIENT
)

type MsgHeader struct {
	To   int64
	From int64
	Type int64
	Size int64
}

func (h MsgHeader) Send(conn net.Conn) {
	buff := new(bytes.Buffer)
	binary.Write(buff, binary.LittleEndian, h)
	conn.Write(buff.Bytes())
}

func (h *MsgHeader) Receive(conn net.Conn) {
	buff := make([]byte, unsafe.Sizeof(*h))
	_, err := conn.Read(buff)
	if err == nil {
		binary.Read(bytes.NewBuffer(buff), binary.LittleEndian, h)
	} else {
		h.Size = 0
		h.Type = MT_NODATA
	}
}

func from866(b []byte) string {
	reader := transform.NewReader(bytes.NewReader(b), charmap.Windows1251.NewDecoder())
	r, _ := io.ReadAll(reader)
	return string(r)
}

func to866(s string) []byte {
	buff := new(bytes.Buffer)
	writer := transform.NewWriter(buff, charmap.Windows1251.NewEncoder())
	defer writer.Close()
	writer.Write([]byte(s))
	return buff.Bytes()
}

type String string

func (s String) to866() []byte {
	buff := new(bytes.Buffer)
	writer := transform.NewWriter(buff, charmap.Windows1251.NewEncoder())
	defer writer.Close()
	writer.Write([]byte(string(s)))
	return buff.Bytes()
}

type Message struct {
	Header MsgHeader
	Data   string
}

func NewMessage(To int64, From int64, Type int64, Data string) *Message {
	return &Message{MsgHeader{To, From, Type, int64(len(Data))}, Data}
}

/*func (m Message) Send(conn net.Conn) {
	m.Header.Send(conn)
	if m.Header.Size > 0 {
		conn.Write(to866(m.Data))
	}
}

func (m *Message) Receive(conn net.Conn) int32 {
	m.Header.Receive(conn)
	if m.Header.Size > 0 {
		buff := make([]byte, m.Header.Size)
		conn.Read(buff)
		m.Data = from866(buff)
	}
	return m.Header.Type
}*/

var clientID int32 = 0

/*func MessageSend(conn net.Conn, To int32, From int32, Type int32, Data string) *Message {
	m := makeMessage(To, From, Type, Data)
	m.Send(conn)
	return m
}*/

/*func MessageCall(To int32, Type int32, Data string) *Message {
	if conn, err := net.Dial("tcp", "localhost:12345"); err != nil {
		log.Println("Server connection error")
		return makeMessage(clientID, To, MT_NODATA, "")
	} else {
		defer conn.Close()
		m := MessageSend(conn, To, clientID, Type, Data)
		m.Receive(conn)
		if m.Header.Type == MT_INIT {
			clientID = m.Header.To
		}
		return m
	}
}*/
