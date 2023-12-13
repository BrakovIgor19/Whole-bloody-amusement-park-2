SELECT * FROM mailpassword;
SELECT * FROM Users;
SELECT * FROM Conversations;
SELECT * FROM Users_Conversations;
SELECT * FROM Messages;

-- Авторизация
SELECT password FROM mailpassword WHERE mail = 'coolMadx@arcadiaBay.us';

-- Получение информации при успешной авторизации
SELECT Users.id, Users.firstname, Users.lastname, Users.nameAvatar FROM Users WHERE id = 1;

-- Получение всех id + name бесед в которых состоит пользователь
WITH inConv(id, is_private_messages) AS
	 (SELECT Conversations.id, Conversations.is_private_messages FROM Users_Conversations
	 INNER JOIN Conversations ON Conversations.id = id_conversation
	 WHERE id_user = 2 AND is_private_messages = TRUE),
	
	 bufT(id_user, id_conv, is_private_messages) AS
	 (SELECT Users_Conversations.id_user, Users_Conversations.id_conversation, inConv.is_private_messages FROM inConv 
	 INNER JOIN Users_Conversations ON inConv.id = Users_Conversations.id_conversation
	 WHERE id_user != 2),
	 
	 bufT2(name, id_user) AS
	 (SELECT CONCAT(Users.firstname, ' ', Users.lastname), Users.id FROM Users 
	 INNER JOIN bufT ON Users.id = bufT.id_user)
	 
SELECT Conversations.id, Conversations.name, Users_Conversations.id_user, Conversations.is_private_messages FROM Users_Conversations
	INNER JOIN Conversations ON Conversations.id = id_conversation
	WHERE id_user = 2 AND is_private_messages = FALSE
UNION ALL
SELECT bufT.id_conv, bufT2.name, bufT2.id_user, bufT.is_private_messages FROM bufT
	INNER JOIN bufT2 ON bufT.id_user = bufT2.id_user;

-- Получить все диалоги в которых состоит пользователь id
SELECT Users_Conversations.id_conversation FROM Users_Conversations
WHERE Users_Conversations.id_user = 1;



