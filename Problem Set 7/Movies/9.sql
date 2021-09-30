SELECT DISTINCT name
FROM people JOIN stars ON people.id = stars.person_id
JOIN movies ON movies.id = stars.movie_id
where movies.year = 2004
ORDER BY people.birth