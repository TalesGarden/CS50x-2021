SELECT AVG(rating) AS AverageRatingMovies2012
from movies m, ratings r
where r.movie_id  = m.id and m.year = 2012