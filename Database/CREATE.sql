
DROP TABLE Messages;
DROP TABLE Users_Conversations;
DROP TABLE Friends;
DROP TABLE MailPassword;
DROP TABLE Conversations;
DROP TABLE Users;

CREATE TABLE Users
(	
	firstName TEXT,
	lastName TEXT,
	nameAvatar TEXT DEFAULT 'default',
	id SERIAL PRIMARY KEY
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

CREATE TABLE Conversations
(	
	id SERIAL PRIMARY KEY,
	name TEXT NOT NULL
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
	id_user INTEGER,
	id_conversation INTEGER,
	FOREIGN KEY (id_user) REFERENCES Users (id),
	FOREIGN KEY (id_conversation) REFERENCES Conversations (id)
);






