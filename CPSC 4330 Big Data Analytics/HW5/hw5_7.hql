-- Justin Thoreson
-- 7 March 2022
-- hw5_7.hql

USE dualcore;

SELECT c.cust_id
FROM customers c
LEFT OUTER JOIN orders o
  ON c.cust_id == o.cust_id
WHERE o.cust_id IS NULL;