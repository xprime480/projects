--
-- CREATE THE SECOND AUTO-PLAYLIST, seldom played 4 star rated songs
--

SELECT
	t.track_artist_display_name AS artist,
	x.total AS total,
	t.track_name AS track
--	t.play_count AS count,
--	t.last_played AS played
--	t.track_id as id
FROM	(
	SELECT
	   --
	   -- Column 'total' is generated as a pseudo-random number so that each
 		-- artist will have only a single song in the generated playlist.
		-- It is a combination of the least significant bits of the last play
		-- time modded with the least significant bits of the current time.
		-- It's random enough and allows up to 60 different orderings.
		--
		(substr(ta.last_played,14,2) || substr(ta.last_played, 12, 2) || substr(ta.last_played, 7, 2)) % (100 + 100 * strftime('%S', 'now') ) as total,
		ta.track_artist_display_name as artist, 
		ta.track_id as id
	FROM
		track ta
	INNER JOIN
		ratings ra
	ON
		ta.track_id = ra.ratings_local_track_id
	WHERE
		ta.in_library = 1
	AND
		ra.ratings_value = 5
	AND
		(julianday('now', 'start of day') - julianday(substr(ta.last_played, 1, 4) || '-' || substr(ta.last_played, 5, 2) || '-' || substr(ta.last_played,7,2), 'start of day')) > 1
	) x
INNER JOIN
	track t
ON
	t.track_id = x.id
GROUP BY
	t.track_artist_display_name
HAVING
	x.total = max(x.total)
ORDER BY
	total DESC
LIMIT
	10
;
