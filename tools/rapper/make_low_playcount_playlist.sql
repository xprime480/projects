
.output new_playlist.txt

.width 25 25 7 7

--
-- CREATE THE THIRD AUTO-PLAYLIST, songs played 1-6 times not played in last week, rated 2-5
--
	t.track_artist_display_name AS Artist,
	t.track_name AS Track,
	t.play_count AS Count, 
	x.total AS total

FROM	(
	SELECT
		count(*) as total,
		ta.track_artist_display_name as artist, 
		ta.track_id as id
	FROM
		track ta
	INNER JOIN
		track tb
	ON
		ta.track_artist_display_name = tb.track_artist_display_name
	INNER JOIN
		ratings ra
	ON
		ta.track_id = ra.ratings_local_track_id
	INNER JOIN
		ratings rb
	ON
		tb.track_id = rb.ratings_local_track_id
	WHERE
		( ta.play_count < tb.play_count  OR	( ta.play_count == tb.play_count AND ta.last_played <= tb.last_played ) )
	AND
		ta.in_library = 1
	AND
		tb.in_library = 1
	AND
		ra.ratings_value > 1
	AND
		rb.ratings_value > 1
	AND
		(julianday('now', 'localtime', 'start of day') - julianday(substr(ta.last_played, 1, 4) || '-' || substr(ta.last_played, 5, 2) || '-' || substr(ta.last_played,7,2), 'localtime', 'start of day')) > 6
	AND
		(julianday('now', 'localtime', 'start of day') - julianday(substr(tb.last_played, 1, 4) || '-' || substr(tb.last_played, 5, 2) || '-' || substr(tb.last_played,7,2), 'localtime', 'start of day')) > 6
	AND
		ta.play_count < 7
	AND
		tb.play_count < 7
	GROUP BY
		ta.track_artist_display_name,
		ta.track_id
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
	t.last_played ASC
;

.output stdout
