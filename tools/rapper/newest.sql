--
-- Select never played songs.
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
	WHERE 
		in_library = 1
	AND
		last_played IS NULL
	)
ORDER BY
	Random
;
