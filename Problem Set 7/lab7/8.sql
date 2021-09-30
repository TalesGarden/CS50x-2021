--In 8.sql, write a SQL query that lists the names of the songs that feature other artists.

select name from songs where name like "%feat%";