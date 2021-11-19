USE bw_db24;

DROP TABLE IF EXISTS SharedWith;
DROP TABLE IF EXISTS Event;
DROP TABLE IF EXISTS Location;
DROP TABLE IF EXISTS Student;
DROP TABLE IF EXISTS Professor;

# Create Tables
CREATE TABLE Professor (
    FacultyID 	INTEGER		NOT NULL,
    FacultyName	VARCHAR(40) 	NOT NULL,
    Email	VARCHAR(100) 	NOT NULL,
    Address	VARCHAR(100),
    PRIMARY KEY (FacultyID)
);

CREATE TABLE Student (
    StudentID	INTEGER		NOT NULL,
    StudentName	VARCHAR(50)  	NOT NULL,
    Email	VARCHAR(100) 	NOT NULL,
    GPA		DECIMAL(4, 3) 	NOT NULL,
    Address	VARCHAR(100),
    TimeZone	VARCHAR(50),
    PRIMARY KEY (StudentID)
);

CREATE TABLE Location (
    BuildingName 	VARCHAR(75) 	NOT NULL,
    RoomNumber 		INT(3)		NOT NULL,
    Address 		VARCHAR(100) 	NOT NULL,
    PRIMARY KEY (BuildingName, RoomNumber)
);

CREATE TABLE Event (
    EventID 		INTEGER		NOT NULL,
    FacultyID		INTEGER 	NOT NULL,
    Title		VARCHAR(100) 	NOT NULL,
    TimeZone 		VARCHAR(50) 	NOT NULL,
    EventStart 		DATETIME 	NOT NULL,
    EventEnd 		DATETIME 	NOT NULL,
    OnlineStatus 	BOOLEAN 	DEFAULT TRUE NOT NULL,
    BuildingName 	VARCHAR(75)	DEFAULT NULL,
    RoomNumber  	INT(3)	        DEFAULT NULL,
    EventDesc		VARCHAR(1000),
    PRIMARY KEY (EventID),
    FOREIGN KEY (FacultyID) REFERENCES Professor(FacultyID)
							ON DELETE CASCADE,
    FOREIGN KEY (BuildingName, RoomNumber) REFERENCES Location(BuildingName, RoomNumber)
							ON UPDATE CASCADE ON DELETE SET NULL
);

CREATE TABLE SharedWith (
    EventID   INTEGER NOT NULL,
    StudentID INTEGER NOT NULL,
    PRIMARY KEY (EventID, StudentID),
    FOREIGN KEY (EventID) REFERENCES Event(EventID)
							ON DELETE CASCADE,
    FOREIGN KEY (StudentID) REFERENCES Student(StudentID)
							ON DELETE CASCADE
);


# Describe Tables
DESC Professor;
DESC Student;
DESC Location;
DESC Event;
DESC SharedWith;

# Insert some data into the tables
INSERT INTO Event (EventID, FacultyID, Title,TimeZone,EventStart,EventEnd,OnlineStatus,EventDesc)
VALUES  (191, 189, "Meeting for BIOL 3350",	"America/Los_Angeles", "2022-06-01 00:21:59", "2022-06-01 01:21:59", 1, "This is an event description"),
		(192, 18, "Meeting for SPAN 4940", "America/Los_Angeles", "2022-03-16 04:10:08", "2022-03-16 05:10:08",	1, "Event descriptions are not necessary"),
		(193, 101, "Meeting for UCOR 4110", "America/Los_Angeles", "2021-12-10 13:07:55", "2021-12-10 14:07:55", 1, "Event descriptions are nice to have"),
		(194, 52, "Meeting for ENGL 1390", "America/Los_Angeles", "2021-10-07 11:21:19", "2021-10-07 12:21:19",	1, "Descriptions can be super-detailed. They can contain up to one thousand characters and can describe everything you need to know about the event in that amount of space."),
		(195, 66, "Meeting for SPAN 3670", "America/Los_Angeles", "2022-05-21 21:19:09", "2022-05-21 22:19:09",	1, "Descriptions can be concise");

INSERT INTO Event (EventID, FacultyID, Title,TimeZone,EventStart,EventEnd)
VALUES  (196, 136, "Meeting for PHYS 4200", "America/Los_Angeles", "2022-01-15 18:56:36", "2022-01-15 19:56:36"),		
		(197, 83, "Meeting for UCOR 2340", "America/Los_Angeles", "2022-03-04 09:24:08", "2022-03-04 10:24:08"),		
		(198, 27, "Meeting for UCOR 4430", "America/Los_Angeles", "2022-04-13 10:50:47", "2022-04-13 11:50:47"),		
		(199, 132, "Meeting for CPSC 1250", "America/Los_Angeles", "2022-04-07 11:23:22", "2022-04-07 12:23:22"),		
		(200, 40, "Meeting for BIOL 4360", "America/Los_Angeles", "2022-02-26 19:02:50", "2022-02-26 20:02:50");

# View data tuples from tables
SELECT * FROM Professor;
SELECT * FROM Student;
SELECT * FROM Location;
SELECT * FROM Event;
SELECT * FROM SharedWith;

# Count number of tuples in each table
SELECT COUNT(*) FROM Professor;
SELECT COUNT(*) FROM Student;
SELECT COUNT(*) FROM Location;
SELECT COUNT(*) FROM Event;
SELECT COUNT(*) FROM SharedWith;

# View five data tuples from each table
SELECT * FROM Professor 	LIMIT 5;
SELECT * FROM Student 		LIMIT 5;
SELECT * FROM Location 		LIMIT 5;
SELECT * FROM Event 		LIMIT 5;
SELECT * FROM SharedWith 	LIMIT 5;


# PDA5: SQL DML Practice
# Part a)

SELECT * FROM Student LIMIT 20;

SELECT W.EventID, S.StudentName
FROM SharedWith W, Student S
WHERE W.StudentID = S.StudentID
LIMIT 20;

SELECT E.EventID, E.Title, S.StudentID, S.StudentName
FROM Event E, SharedWith W, Student S
WHERE E.EventID = W.EventID AND W.StudentID = S.StudentID AND S.StudentID % 4 = 0
LIMIT 20;

SELECT TRUNCATE(S.GPA, 0), max(S.GPA)
FROM Student S
GROUP BY TRUNCATE(S.GPA, 0)
LIMIT 20; 

SELECT TRUNCATE(S.GPA, 0), count(S.GPA)
FROM Student S
GROUP BY TRUNCATE(S.GPA, 0)
LIMIT 20; 

# Part b)

INSERT INTO Location
VALUES ("Center for Science and Innovation", 101, "111 25th Avenue, Bellevue, WA 98765-1090"),
	   ("Center for Science and Innovation", 102, "222 50th Avenue, Portland, OR 97531-1090"),
	   ("Center for Science and Innovation", 103, "333 75th Avenue, Los Angeles, CA 98989-1090"),
	   ("Center for Science and Innovation", 204, "444 100th Avenue, Cupertino, CA 87654-1090"),
	   ("Center for Science and Innovation", 205, "901 12th Avenue, Seattle, WA 98122-1090");

UPDATE Location
SET Address = "901 12th Avenue, Seattle, WA 98122-1090"
WHERE RoomNumber = 101;

UPDATE Location
SET Address = "901 12th Avenue, Seattle, WA 98122-1090"
WHERE BuildingName = "Center for Science and Innovation";

DELETE FROM Location
WHERE BuildingName = "Center for Science and Innovation";

DELETE FROM Student
WHERE StudentID = 2001;
