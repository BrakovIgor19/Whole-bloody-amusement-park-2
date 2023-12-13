-- Общий чатик
INSERT INTO Conversations(name, is_private_messages) VALUES ('Общий чатик', FALSE);

-- Макс Колфилд
SELECT InsertUser('coolMax@arcadiaBay.us', 'chloe+max', 'Макс', 'Колфилд', 'Max Caulfield.gif');

-- Хлоя Прайс
SELECT InsertUser('ChloePrice@arcadiaBay.us', 'max+chloe', 'Хлоя', 'Прайс', 'Chloe Price.gif');

-- Виктория Чейз
SELECT InsertUser('TheBestPhotographer@arcadiaBay.us', 'bestThebestGirl', 'Виктория', 'Чейз', 'Victoria Chase.gif');

-- Марта Кивельсон
SELECT InsertUser('AstronautIO@NASA.us', 'sorryBurton', 'Марта', 'Кивельсон', 'Martha Kivelson.jpg');

-- Матвей Безмолвный
SELECT InsertUser('SilentMatvey@Roscosmos.us', 'Тишина', 'Матвей', 'Безмолвный', 'Матвей Безмолвный.jpg');

-- Марат Бадамшин
SELECT InsertUser('Badamshin@ozon.ru', 'Марат4', 'Марат', 'Бадамшин', 'Марат Бадамшин.jpg');

-- Тимерлан Айранов
SELECT InsertUser('Timoxa@anime.ru', 'Мухтаров', 'Тимерлан', 'Айранов', 'Тимерлан Айранов.jpg');

-- Даша Юровская
SELECT InsertUser('DashaYurovskaya@volgodonsk.ru', 'Lapulya', 'Даша', 'Юровская', 'Даша Юровская.gif');

-- Саша Лестная
SELECT InsertUser('OnPositive@sun.ru', 'Positive', 'Саша', 'Лестная', 'Саша Лестная.jpg');

-- XapTMaH19
SELECT InsertUser('XapTMaH19@mail.ru', '19', 'XapTMaH', '19', 'XapTMaH19.jpg');

-- Ио
SELECT InsertUser('Io@Space.live', 'Машина', 'Ио', '', 'Ио.jpg');

-- Космическая беседа
INSERT INTO Conversations(name, is_private_messages) VALUES ('Почётный клуб космонавтов', FALSE);
INSERT INTO Users_Conversations(id_user, id_conversation) VALUES (5, 68);
INSERT INTO Users_Conversations(id_user, id_conversation) VALUES (4, 68);
INSERT INTO Users_Conversations(id_user, id_conversation) VALUES (11, 68);

-- Добавление космонавтов в беседу


-- Сохранение сообщения
INSERT INTO Messages(data, id_conversation, id_user) VALUES ('Замутим мошпит девчуля?', 1, 1);

INSERT INTO Messages(data, id_conversation, id_user) VALUES ('12345', 1, 10);
