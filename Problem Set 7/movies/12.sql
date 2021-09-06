SELECT title
FROM people JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
where people.name = 'Johnny Depp'
AND stars.movie_id IN (
	SELECT stars.movie_id
	FROM people JOIN stars ON people.id = stars.person_id
	WHERE people.name = 'Helena Bonham Carter'
)