-- Justin Thoreson
-- 7 March 2022
-- hw5_10.hql

USE dualcore;

SELECT r.message
FROM ratings r
WHERE r.message LIKE '%ten times more%';