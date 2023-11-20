
INSERT INTO Users VALUES ('Макс', 'Колфилд');
INSERT INTO mailpassword VALUES ('coolMax@arcadiaBay.us', 'chloe+max', (SELECT id FROM Users ORDER BY id DESC LIMIT 1));

INSERT INTO Users VALUES ('Хлоя', 'Прайс');
INSERT INTO mailpassword VALUES ('ChloePrice@arcadiaBay.us', 'max+chloe', (SELECT id FROM Users ORDER BY id DESC LIMIT 1));

INSERT INTO Users VALUES ('Виктория', 'Чейз');
INSERT INTO mailpassword VALUES ('TheBestPhotographer@arcadiaBay.us', 'bestThebestgirl', (SELECT id FROM Users ORDER BY id DESC LIMIT 1));



DELETE FROM Users
WHERE id > 0;