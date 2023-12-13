CREATE OR REPLACE FUNCTION InsertUser(_mail VARCHAR, password VARCHAR, firstName VARCHAR, lastName VARCHAR, nameAvatar VARCHAR) RETURNS int AS
$$
DECLARE
	id_u integer;
	id_c integer;
	x_id integer;
BEGIN
   IF (SELECT EXISTS (SELECT FROM mailpassword WHERE mailpassword.mail = _mail)) THEN
   		RETURN -1;
   ELSE
  		INSERT INTO Users(firstName, lastName, nameAvatar) VALUES (firstName, lastName, nameAvatar) RETURNING Users.id INTO id_u;
  		INSERT INTO mailpassword(mail, password, id_user) VALUES (_mail, password, id_u);
		INSERT INTO Users_Conversations(id_user, id_conversation) VALUES (id_u, 1);
		INSERT INTO Conversations(name, is_private_messages) VALUES (CONCAT(firstName, ' ', lastName), FALSE) RETURNING Conversations.id INTO id_c;
		INSERT INTO Users_Conversations(id_user, id_conversation) VALUES (id_u, id_c); 
		FOR x_id IN (SELECT * FROM Users)
		LOOP
			IF (x_id != id_u) THEN
				INSERT INTO Conversations(is_private_messages) VALUES (TRUE) RETURNING Conversations.id INTO id_c;
				INSERT INTO Users_Conversations(id_user, id_conversation) VALUES (id_u, id_c);    		
				INSERT INTO Users_Conversations(id_user, id_conversation) VALUES (x_id, id_c);
			END IF;
  		END LOOP;
		
		RETURN id_u;
   END IF;
END
$$ LANGUAGE PLPGSQL;

 unnest(array[100, 110, 153, 100500]), '2015-01-01', 3;


DROP FUNCTION insertuser(character varying,character varying,character varying,character varying, character varying);