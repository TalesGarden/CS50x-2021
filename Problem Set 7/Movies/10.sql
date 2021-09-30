SELECT DISTINCT name
FROM people JOIN directors ON people.id = directors.person_id
join ratings ON ratings.movie_id = directors.movie_id
where ratings.rating >= 9.0