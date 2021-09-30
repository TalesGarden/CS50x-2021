--In 7.sql, write a SQL query that returns the average energy of songs that are by Drake.

SELECT AVG(energy)
FROM songs
WHERE songs.artist_id IN (select id from artists WHERE artists.name = 'Drake');