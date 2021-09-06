SELECT title
FROM people JOIN stars ON people.id = stars.person_id
JOIN movies ON STARS.movie_id = movies.id
JOIN ratings ON ratings.movie_id = movies.id
where people.name = 'Chadwick Boseman'
ORDER BY ratings.rating DESC
LIMIT 5;