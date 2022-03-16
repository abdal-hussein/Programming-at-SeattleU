-- Justin Thoreson
-- 7 March 2022
-- hw5_6.hql

USE dualcore;

SELECT COUNT(cust_id) AS num_cust
FROM (SELECT o.cust_id AS cust_id, SUM(p.price) AS total_spent
      FROM orders o
      JOIN order_details d
        ON o.order_id == d.order_id
      JOIN products p
        ON d.prod_id == p.prod_id
      GROUP BY o.cust_id) cust_expenses
WHERE total_spent > 300000;