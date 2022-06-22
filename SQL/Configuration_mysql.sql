#create database db2
CREATE DATABASE db2;

#use new database
USE db2;

# create hotel
CREATE TABLE hotel
(
hotel_id INT(15) NOT NULL PRIMARY KEY,
hotel_address VARCHAR(50) NOT NULL,
hotel_level INT(1) NOT NULL,
zip_code INT(5) NOT NULL,
hotel_name VARCHAR(30) NOT NULL
);

# create manager
CREATE TABLE manager
(
manager_id INT(15) NOT NULL PRIMARY KEY,
hotel_id INT(15) NOT NULL,
manager_password VARCHAR(20) NOT NULL,
manager_name VARCHAR(30) NOT NULL,
phone_number VARCHAR(15) NOT NULL,
manager_address VARCHAR(50) NOT NULL,
manager_authority VARCHAR(10) NOT NULL,
FOREIGN KEY(hotel_id) REFERENCES hotel(hotel_id)
)ENGINE=INNODB CHARSET=utf8;

# create room
CREATE TABLE room
(
room_id INT(15) NOT NULL PRIMARY KEY,
room_type VARCHAR(20) NOT NULL,
hotel_id INT(15) NOT NULL,
room_price INT(4) NOT NULL,
room_status VARCHAR(10) NOT NULL,
check_in_date DATETIME DEFAULT NULL,
check_out_date DATETIME DEFAULT NULL,
FOREIGN KEY(hotel_id) REFERENCES hotel(hotel_id)
)ENGINE=INNODB CHARSET=utf8;

# create customer
CREATE TABLE customer
(
customer_id VARCHAR(20) NOT NULL PRIMARY KEY,
customer_name VARCHAR(30) NOT NULL,
phone_number VARCHAR(15) NOT NULL,
customer_address VARCHAR(50) NOT NULL,
account_number VARCHAR(20) NOT NULL,
room_id INT(15) NOT NULL,
FOREIGN KEY(room_id) REFERENCES room(room_id)
)ENGINE=INNODB CHARSET=utf8;

#insert into hotel table
INSERT INTO hotel (hotel_id, hotel_address, hotel_level, zip_code, hotel_name)
VALUES(06901001, "700 East Main Street", 4, 06901, "The Stamford");
INSERT INTO hotel (hotel_id, hotel_address, hotel_level, zip_code, hotel_name)
VALUES(10036002, "866 3rd Avenue", 5, 10036, "Midtown East");
INSERT INTO hotel (hotel_id, hotel_address, hotel_level, zip_code, hotel_name)
VALUES(90019003, "40 Commerce Ln, Rt 2 and Rt 4", 2, 90019, "Super 8");

#insert into manager table
INSERT INTO manager
VALUES(1001, 06901001, 'bochen', 'Bochen Hu', '9599299332', '65 glenbrook rd', 'super');
INSERT INTO manager
VALUES(1002, 06901001, 'wenrui', 'Wenrui Wang', '9174157348', '1011 Washington Blvd', 'super');
INSERT INTO manager
VALUES(2001, 10036002, 'yinghao', 'Yinghao Wang', '4754390108', '866 3rd Avenue', 'normal');
INSERT INTO manager
VALUES(2002, 10036002, 'meng', 'Meng Zhang', '8606348093', '485 7th Avenue', 'normal');
INSERT INTO manager
VALUES(3001, 90019003, 'zhe', 'Zhe Wang', '4759771510', '22769 Three Notch Rd', 'normal');
INSERT INTO manager
VALUES(3002, 90019003, 'xiaoyi', 'Xiaoyi Xiong', '6317108925', '40 Commerce Ln', 'normal');

#insert into room table
INSERT INTO room
VALUES(1101, 'Single Room', 6901001, 160, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(1102, 'Single Room', 6901001, 170, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(1103, 'Single Room', 6901001, 150, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(1104, 'Single Room', 6901001, 180, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(1105, 'Single Room', 6901001, 190, 'Empty', NULL, NULL);

INSERT INTO room
VALUES(1201, 'Double Room', 6901001, 210, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(1202, 'Double Room', 6901001, 220, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(1203, 'Double Room', 6901001, 240, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(1204, 'Double Room', 6901001, 230, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(1205, 'Double Room', 6901001, 249, 'Empty', NULL, NULL);

INSERT INTO room
VALUES(1301, 'Triple Room', 6901001, 260, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(1302, 'Triple Room', 6901001, 270, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(1303, 'Triple Room', 6901001, 290, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(1304, 'Triple Room', 6901001, 280, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(1305, 'Triple Room', 6901001, 300, 'Empty', NULL, NULL);

INSERT INTO room
VALUES(1401, 'VIP Room', 6901001, 310, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(1402, 'VIP Room', 6901001, 350, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(1403, 'VIP Room', 6901001, 380, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(1404, 'VIP Room', 6901001, 420, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(1405, 'VIP Room', 6901001, 1080, 'Empty', NULL, NULL);


#insert for 10036002 hotel
INSERT INTO room
VALUES(2101, 'Single Room', 10036002, 160, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(2102, 'Single Room', 10036002, 170, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(2103, 'Single Room', 10036002, 150, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(2104, 'Single Room', 10036002, 180, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(2105, 'Single Room', 10036002, 190, 'Empty', NULL, NULL);

INSERT INTO room
VALUES(2201, 'Double Room', 10036002, 210, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(2202, 'Double Room', 10036002, 220, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(2203, 'Double Room', 10036002, 240, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(2204, 'Double Room', 10036002, 230, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(2205, 'Double Room', 10036002, 249, 'Empty', NULL, NULL);

INSERT INTO room
VALUES(2301, 'Triple Room', 10036002, 260, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(2302, 'Triple Room', 10036002, 270, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(2303, 'Triple Room', 10036002, 290, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(2304, 'Triple Room', 10036002, 280, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(2305, 'Triple Room', 10036002, 300, 'Empty', NULL, NULL);

INSERT INTO room
VALUES(2401, 'VIP Room', 10036002, 310, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(2402, 'VIP Room', 10036002, 350, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(2403, 'VIP Room', 10036002, 380, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(2404, 'VIP Room', 10036002, 420, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(2405, 'VIP Room', 10036002, 1080, 'Empty', NULL, NULL);


#insert for 90019003 hotel
INSERT INTO room
VALUES(3101, 'Single Room', 90019003, 160, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(3102, 'Single Room', 90019003, 170, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(3103, 'Single Room', 90019003, 150, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(3104, 'Single Room', 90019003, 180, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(3105, 'Single Room', 90019003, 190, 'Empty', NULL, NULL);

INSERT INTO room
VALUES(3201, 'Double Room', 90019003, 210, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(3202, 'Double Room', 90019003, 220, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(3203, 'Double Room', 90019003, 240, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(3204, 'Double Room', 90019003, 230, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(3205, 'Double Room', 90019003, 249, 'Empty', NULL, NULL);

INSERT INTO room
VALUES(3301, 'Triple Room', 90019003, 260, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(3302, 'Triple Room', 90019003, 270, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(3303, 'Triple Room', 90019003, 290, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(3304, 'Triple Room', 90019003, 280, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(3305, 'Triple Room', 90019003, 300, 'Empty', NULL, NULL);

INSERT INTO room
VALUES(3401, 'VIP Room', 90019003, 310, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(3402, 'VIP Room', 90019003, 350, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(3403, 'VIP Room', 90019003, 380, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(3404, 'VIP Room', 90019003, 420, 'Empty', NULL, NULL);
INSERT INTO room
VALUES(3405, 'VIP Room', 90019003, 1080, 'Empty', NULL, NULL);


#insert into customer table
INSERT INTO customer
VALUES('999999999', 'Dan Lee', '18829515250', 'Xi\'an', '88888888', 1101);