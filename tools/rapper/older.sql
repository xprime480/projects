--
-- Select songs that have not been played in over 27 days.
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
		(julianday('now', 'localtime', 'start of day') - julianday(substr(t.last_played, 1, 4) || '-' || substr(t.last_played, 5, 2) || '-' || substr(t.last_played,7,2), 'localtime', 'start of day')) > 27
	AND
		in_library = 1
	)
ORDER BY
	Random
;
