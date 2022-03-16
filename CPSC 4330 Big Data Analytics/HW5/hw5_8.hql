-- Justin Thoreson
-- 7 March 2022
-- hw5_8.hql

USE dualcore;

-- View is created so query result can be used in hw5_9.hql
DROP VIEW IF EXISTS lowest_rating_info;

CREATE VIEW lowest_rating_info AS
SELECT *
FROM (SELECT r.prod_id as prod_id, COUNT(r.prod_id) as num_ratings, AVG(r.rating) as avg_rating
      FROM ratings r
      GROUP BY r.prod_id) avg_prod_ratings
WHERE num_ratings >= 50
ORDER BY avg_rating ASC
LIMIT 1;

SELECT *
FROM lowest_rating_info;