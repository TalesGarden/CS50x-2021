-- Keep a log of any SQL queries you execute as you solve the mystery.

select * from people
 -- id | name | phone_number | passport_number | license_plate
--205082 | Pamela | (113) 555-7544 | 1050247273 | 5CIO816
--210245 | Jordan | (328) 555-9658 | 7951366683 | HW0488P
--210641 | Heather| (502) 555-6712 | 4356447308 | 

select * from crime_scene_reports
--id | year | month | day | street | description
--1 | 2020 | 1 | 1 | Chamberlin Street | Credit card fraud took place at 00:53. Two people witnessed the event.
--2 | 2020 | 1 | 1 | Zlatkova Street | Burglary took place at 05:23. Two people witnessed the event.
--3 | 2020 | 1 | 1 | Bowden Boulevard | Shoplifting took place at 20:48. Two people witnessed the event.

select * from courthouse_security_logs;
--id | year | month | day | hour | minute | activity | license_plate
--1 | 2020 | 7 | 25 | 7 | 1 | entrance | 0R0FW39
--2 | 2020 | 7 | 25 | 7 | 31 | entrance | 97O6H62
--3 | 2020 | 7 | 25 | 7 | 58 | entrance | 5840J5X

select * from airports;
--id | abbreviation | full_name | city
--1 | ORD | O'Hare International Airport | Chicago
--2 | PEK | Beijing Capital International Airport | Beijing
--3 | LAX | Los Angeles International Airport | Los Angeles
--4 | LHR | Heathrow Airport | London
--5 | DFS | Dallas/Fort Worth International Airport | Dallas

select * from flights;
--id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
--1 | 8 | 7 | 2020 | 7 | 28 | 17 | 50
--2 | 2 | 8 | 2020 | 7 | 30 | 12 | 44
--3 | 1 | 8 | 2020 | 7 | 26 | 13 | 56

select * from passengers

--flight_id | passport_number | seat
--1 | 2400516856 | 2C
--1 | 9183348466 | 3B
--1 | 9628244268 | 4B

CREATE TABLE crime_scene_reports (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    street TEXT,
    description TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE interviews (
    id INTEGER,
    name TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    transcript TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE courthouse_security_logs (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    activity TEXT,
    license_plate TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE atm_transactions (
    id INTEGER,
    account_number INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    atm_location TEXT,
    transaction_type TEXT,
    amount INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE bank_accounts (
    account_number INTEGER,
    person_id INTEGER,
    creation_year INTEGER,
    FOREIGN KEY(person_id) REFERENCES people(id)
);
CREATE TABLE airports (
    id INTEGER,
    abbreviation TEXT,
    full_name TEXT,
    city TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE flights (
    id INTEGER,
    origin_airport_id INTEGER,
    destination_airport_id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    PRIMARY KEY(id),
    FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
    FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
);
CREATE TABLE passengers (
    flight_id INTEGER,
    passport_number INTEGER,
    seat TEXT,
    FOREIGN KEY(flight_id) REFERENCES flights(id)
);
CREATE TABLE phone_calls (
    id INTEGER,
    caller TEXT,
    receiver TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    duration INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE people (
    id INTEGER,
    name TEXT,
    phone_number TEXT,
    passport_number INTEGER,
    license_plate TEXT,
    PRIMARY KEY(id)
);
select name from people,courthouse_security_logs  WHERE people.license_plate = courth
thouse_security_logs.license_plate


SELECT
    description
FROM
    crime_scene_reports
WHERE
    day = "28"
    AND month = "7"
    AND year = "2020"
    AND street = "Chamberlin Street" -- Get the transcriptions from the interviews on the day of the crime


SELECT
    transcript
FROM
    interviews
WHERE
    day = "28"
    AND month = "7"
    AND year = "2020"
    AND transcript like "%courthouse%" -- Get how the actvity is describe
