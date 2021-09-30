SELECT  DISTINCT people.name
FROM people JOIN stars ON people.id = stars.person_id
WHERE name != 'Kevin Bacon'
AND stars.movie_id IN (
	SELECT stars.movie_id
	FROM stars JOIN people ON stars.person_id = people.id
	WHERE people.name = 'Kevin Bacon' and people.birth = '1958'
)