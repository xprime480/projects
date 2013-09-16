--
-- Select 4 star songs that are in the library and haven't been 
-- played in at least 4 days
--

SELECT 
	Id,
	Artist
FROM
	(
	SELECT
		track_id        AS 'Id', 
		track_artist_id AS 'Artist',
		random()        AS 'Random'
	FROM
		track t
	INNER JOIN
		ratings r
	ON
		t.track_id = r.ratings_local_track_id
	WHERE 
		(julianday('now', 'localtime', 'start of day') - julianday(substr(t.last_played, 1, 4) || '-' || substr(t.last_played, 5, 2) || '-' || substr(t.last_played,7,2), 'localtime', 'start of day')) > 6
	AND
		in_library = 1
	AND
		r.ratings_value = 4
	)
ORDER BY
	Random
;

