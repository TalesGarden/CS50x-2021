--In 6.sql, write a SQL query that lists the names of songs that are by Post Malone.
SELECT name FROM songs WHERE songs.artist_id in (select id from artists where name ='Post Malone')