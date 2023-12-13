CREATE SCHEMA Vestimo;

SET search_path TO Vestimo

DROP TABLE Messages;
DROP TABLE Users_Conversations;
DROP TABLE Friends;
DROP TABLE Subscribers;
DROP TABLE MailPassword;
DROP TABLE Conversations;
DROP TABLE Users;

CREATE TABLE Users
(
	id SERIAL PRIMARY KEY,
	firstName TEXT,
	lastName TEXT,
	nameAvatar TEXT DEFAULT 'default.jpg',
	age INTEGER DEFAULT NULL,
	city TEXT DEFAULT NULL,
	inspirational_quote TEXT DEFAULT NULL
);

CREATE TABLE MailPassword
(		
	mail VARCHAR(64) NOT NULL,
	password VARCHAR(32) NOT NULL,
	id_user INTEGER,
	FOREIGN KEY (id_user) REFERENCES Users (id)
);

CREATE TABLE Friends
(		
	id_user INTEGER,
	id_friend INTEGER,
	FOREIGN KEY (id_user) REFERENCES Users (id),
	FOREIGN KEY (id_friend) REFERENCES Users (id)
);

CREATE TABLE Subscribers
(		
	id_user INTEGER,
	id_friend INTEGER,
	FOREIGN KEY (id_user) REFERENCES Users (id),
	FOREIGN KEY (id_friend) REFERENCES Users (id)
);

CREATE TABLE Conversations
(	
	id SERIAL PRIMARY KEY,
	name TEXT DEFAULT NULL,
	is_private_messages BOOLEAN NOT NULL
);

CREATE TABLE Users_Conversations
(		
	id_user INTEGER,
	id_conversation INTEGER,
	FOREIGN KEY (id_user) REFERENCES Users (id),
	FOREIGN KEY (id_conversation) REFERENCES Conversations (id)
);

CREATE TABLE Messages
(	
	data TEXT,
	date DATE DEFAULT '1000-7-7',
	id_conversation INTEGER,
	id_user INTEGER,
	FOREIGN KEY (id_user) REFERENCES Users (id),
	FOREIGN KEY (id_conversation) REFERENCES Conversations (id)
);






