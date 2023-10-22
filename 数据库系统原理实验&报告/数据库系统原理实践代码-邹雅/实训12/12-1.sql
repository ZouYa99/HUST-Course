 # 请将你实现flight_booking数据库的语句写在下方：
drop database if exists flight_booking;
create database flight_booking;
use flight_booking;
-- #航空公司
create table airline(
    airline_id int PRIMARY KEY  AUTO_INCREMENT,
    `name` varchar(30) not null,
    iata char(2) not null unique,
    airport_id int not null
);
-- #民航飞机
create table airplane(
    airplane_id int PRIMARY KEY  AUTO_INCREMENT,
    `type` varchar(50) not null,
    capacity smallint not null,
    identifier varchar(50) not null,
    airline_id int not null
);
-- #机场
create table airport(
    airport_id int PRIMARY KEY AUTO_INCREMENT,
    iata char(3) not null unique,
    icao char(4) not null unique,
    `name` varchar(50) not null,
    city varchar(50),
    country varchar(50),
    latitude decimal(11,8),
    longitude decimal(11,8)
);
alter table airline
add CONSTRAINT FK_airline_airport 
FOREIGN KEY (airport_id) REFERENCES airport(airport_id);

alter table airplane
add CONSTRAINT FK_airplane_airline 
FOREIGN KEY (airline_id) REFERENCES airline(airline_id);

create index name_idx on airport(`name`);
-- #航班表
create table flight(
    flight_id int PRIMARY KEY AUTO_INCREMENT,
    departure datetime not null,
    arrival datetime not null,
    duration smallint not null,
    flight_no char(8) not null,
    airline_id int not null,
    airplane_id int not null,
    `from` int not null,
    `to` int not null,
     constraint FK_flight_airline FOREIGN KEY (airline_id) REFERENCES airline(airline_id),
     constraint FK_flight_airplane FOREIGN KEY (airplane_id) REFERENCES airplane(airplane_id),
     CONSTRAINT FK_flight_from FOREIGN KEY (`from`) REFERENCES airport(airport_id),
     CONSTRAINT FK_flight_to FOREIGN KEY (`to`) REFERENCES airport(airport_id)
);
-- #航班常规调度表
create table flightschedule(
    flight_no char(8) PRIMARY KEY,
    departure time not null,
    arrival time not null,
    duration smallint not null,
    monday tinyint default 0,
    tuesday tinyint default 0,
    wednesday tinyint default 0,
    thursday tinyint default 0,
    friday tinyint default 0,
    saturday tinyint default 0,
    sunday tinyint default 0,
    airline_id int not null,
    `from` int not null,
    `to` int not null,
    constraint FK_flightschedule_airline FOREIGN KEY (airline_id) REFERENCES airline(airline_id),
    CONSTRAINT FK_flightschedule_from FOREIGN KEY (`from`) REFERENCES airport(airport_id),
    CONSTRAINT FK_flightschedule_to FOREIGN KEY (`to`) REFERENCES airport(airport_id)
);
alter table flight
add CONSTRAINT FK_flight_flightschedule FOREIGN KEY (flight_no) REFERENCES flightschedule(flight_no);
-- #旅客
create table passenger(
    passenger_id int PRIMARY KEY  AUTO_INCREMENT,
    id char(18) not null unique,
    firstname varchar(50) not null,
    lastname varchar(50) not null,
    mail varchar(50),
    phone varchar(20) not null,
    sex char(1) not null,
    dob date
);
-- #机票
create table ticket(
    ticket_id int PRIMARY KEY  AUTO_INCREMENT,
    seat char(4),
    price decimal(10,2) not null,
    flight_id int not null,
    passenger_id int not null,
    user_id int not null,
    CONSTRAINT FK_ticket_passenger FOREIGN KEY (passenger_id) REFERENCES passenger(passenger_id),
    CONSTRAINT FK_ticket_flight FOREIGN KEY (flight_id) REFERENCES flight(flight_id)
);
-- #用户
create table `user`(
    user_id int PRIMARY KEY  AUTO_INCREMENT,
    firstname varchar(50) not null,
    lastname varchar(50) not null,
    dob date not null,
    sex char(1) not null,
    email varchar(50),
    phone varchar(30),
    username varchar(20) not null unique,
    `password` char(32) not null,
    admin_tag tinyint default 0 not null
);
alter table ticket
add CONSTRAINT FK_ticket_user
FOREIGN KEY (user_id) REFERENCES `user`(user_id);

