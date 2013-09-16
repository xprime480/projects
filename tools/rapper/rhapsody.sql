--
-- SQL statements to be classified later.
--

SELECT * FROM track where  in_library = 1 order by last_played

====================================================================

select * from ratings where ratings_value >0

====================================================================

SELECT count(*) FROM track where  in_library = 1
UNION ALL 
SELECT count(*) FROM ratings where ratings_value > 0

====================================================================

SELECT 
	t.TRACK_ARTIST_DISPLAY_NAME as ARTIST,
	t.TRACK_NAME as TRACK,
	r.RATINGS_VALUE as RATING,
	t.PLAY_COUNT as COUNT,
	julianday('now', 'start of day') - julianday(substr(t. LAST_PLAYED, 1, 4) || '-' || substr(t.LAST_PLAYED, 5, 2) || '-' || substr(t.LAST_PLAYED,7,2), 'start of day') as DAYS,
	abs(RANDOM() % 10000 / 100.0) as JITTER
FROM 
	track t
INNER JOIN
	ratings r
ON
	t.track_id = r. RATINGS_LOCAL_TRACK_ID
WHERE
	r.RATINGS_VALUE > 3
ORDER BY
	t.LAST_PLAYED DESC

====================================================================

SELECT
	TRACK_ARTIST_DISPLAY_NAME as ARTIST,
	TRACK_NAME as TRACK, 
	IN_LIBRARY as LOCAL,
	substr(LAST_PLAYED, 1, 4) || '-' || substr(LAST_PLAYED, 5, 2) || '-' || substr(LAST_PLAYED,7,2) as LAST_PLAYED
FROM
track
WHERE
in_library = 0
ORDER BY
last_played DESC

====================================================================

SELECT
	COUNT(*)
FROM
track
WHERE
in_library = 0 
AND
last_played IS NULL


====================================================================

SELECT
	count(*)
FROM
	track
WHERE
	last_played IS NOT NULL
AND
	in_library = 1

====================================================================

SELECT 
	t.TRACK_ARTIST_DISPLAY_NAME as ARTIST,
	t.TRACK_NAME as TRACK,
	t.ALBUM_NAME as ALBUM,
	r.RATINGS_VALUE as RATING,
	t.PLAY_COUNT as COUNT,
	julianday('now', 'start of day') - julianday(substr(t. LAST_PLAYED, 1, 4) || '-' || substr(t.LAST_PLAYED, 5, 2) || '-' || substr(t.LAST_PLAYED,7,2), 'start of day') as DAYS,
	abs(RANDOM() % 10000 / 100.0) as JITTER
FROM 
	track t
INNER JOIN
	ratings r
ON
	t.track_id = r. RATINGS_LOCAL_TRACK_ID
WHERE
	r.RATINGS_VALUE > 0
AND
	t.in_library = 1
ORDER BY
	t.LAST_PLAYED DESC

====================================================================
--
-- CREATE THE FIRST AUTO-PLAYLIST, old 4 and 5 star rated songs
--

SELECT 
	t.ARTIST,
	t.TRACK,
	t.ALBUM,
	r.RATINGS_VALUE as RATING,
	t.COUNT,
	t.JITTER
FROM	(
		SELECT
			TRACK_ID,
			LAST_PLAYED,
			TRACK_ARTIST_DISPLAY_NAME as ARTIST,
			TRACK_NAME as TRACK,
			ALBUM_NAME as ALBUM,
			PLAY_COUNT as COUNT,
			julianday('now', 'start of day') - julianday(substr(LAST_PLAYED, 1, 4) || '-' || substr(LAST_PLAYED, 5, 2) || '-' || substr(LAST_PLAYED,7,2), 'start of day') as DAYS,
			abs(RANDOM() % 10000 / 100.0) as JITTER
		FROM	
			track
		WHERE
			in_library = 1
	) t
INNER JOIN
	ratings r
ON
	t.track_id = r. RATINGS_LOCAL_TRACK_ID
WHERE
	( r.RATINGS_VALUE = 5 AND t.DAYS > 0 )
OR
	( r.RATINGS_VALUE = 4 AND t.DAYS > 6 )
ORDER BY
	t.LAST_PLAYED DESC

====================================================================
	

====================================================================

SELECT
	count(*) 
FROM
	track t
WHERE
	in_library != 1
AND
	EXISTS	(
		SELECT
			ratings_local_track_id r
		FROM
			ratings
		WHERE
			t.track_id = ratings_local_track_id
		AND
			ratings_value > 0
		)



====================================================================
--
-- CREATE THE THIRD AUTO-PLAYLIST, songs played 1-6 times not played in last week, rated 2-5
--

SELECT
	t.track_artist_display_name AS artist,
	x.total AS total,
	t.track_name AS track,
	t.play_count AS count, 
	t.last_played AS played,
	t.track_id as id
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

====================================================================

SELECT julianday('now')
UNION ALL
SELECT julianday('now', 'localtime')
UNION ALL
SELECT julianday('now', 'start of day')
UNION ALL
SELECT julianday('now', 'localtime', 'start of day')
UNION ALL
SELECT julianday('now', 'start of day', 'localtime')
UNION ALL
SELECT julianday('2013-04-04') 
UNION ALL
SELECT julianday('2013-04-04', 'localtime') 
UNION ALL
SELECT julianday('2013-04-04', 'start of day') 
UNION ALL
SELECT julianday('2013-04-04', 'localtime', 'start of day') 
UNION ALL
SELECT julianday('2013-04-04', 'start of day', 'localtime') 

UNION ALL

SELECT julianday('now') - julianday('2013-04-04') 
UNION ALL
SELECT julianday('now', 'localtime') - julianday('2013-04-04', 'localtime') 
UNION ALL
SELECT julianday('now', 'start of day') - julianday('2013-04-04', 'start of day') 
UNION ALL
SELECT julianday('now', 'localtime', 'start of day') - julianday('2013-04-04', 'localtime', 'start of day') 
UNION ALL
SELECT julianday('now', 'start of day', 'localtime') - julianday('2013-04-04', 'start of day', 'localtime') 

====================================================================

SELECT 
	count(*), in_library, min(ifnull(play_count, 0),1) as played 
FROM 
	track 
GROUP BY 
	in_library, min(ifnull(play_count, 0), 1)


====================================================================

SELECT
	track_name AS 'Track',
	track_artist_display_name AS 'Artist',
	date_added AS 'Added'
FROM
	track
WHERE
	in_library = 0
AND
	play_count IS NULL
AND
	(julianday('now', 'localtime', 'start of day') - julianday(substr(date_added, 1, 4) || '-' || substr(date_added, 5, 2) || '-' || substr(date_added,7,2), 'localtime', 'start of day')) <= 30

====================================================================

SELECT
	track_name AS 'Track',
	track_artist_display_name AS 'Artist',
	date_added AS 'Added'
FROM
	track
WHERE
	in_library = 1
AND
	play_count IS NULL
AND
	(julianday('now', 'localtime', 'start of day') - julianday(substr(date_added, 1, 4) || '-' || substr(date_added, 5, 2) || '-' || substr(date_added,7,2), 'localtime', 'start of day')) > 30


====================================================================

UPDATE
	track
SET
	in_library = 1
WHERE
	in_library = 0
AND
	play_count IS NULL
AND
	(julianday('now', 'localtime', 'start of day') - julianday(substr(date_added, 1, 4) || '-' || substr(date_added, 5, 2) || '-' || substr(date_added,7,2), 'localtime', 'start of day')) <= 30
	

====================================================================

SELECT
	track_name AS 'Track',
	track_artist_display_name AS 'Artist',
	date_added AS 'Added'
FROM
	track t
WHERE
	in_library != 1
AND
	EXISTS	(
		SELECT
			ratings_local_track_id r
		FROM
			ratings
		WHERE
			t.track_id = ratings_local_track_id
		AND
			ratings_value > 0
		)

====================================================================

SELECT
	count(*)
FROM
	ratings
UNION ALL
SELECT
	count(*)
FROM
	track t
WHERE
	last_played IS NULL
AND
	NOT EXISTS
	(
		SELECT
			ratings_id
		FROM
			ratings r
		WHERE
			t.track_id = r.ratings_local_track_id

	)

====================================================================

SELECT
	track_name AS 'Track',
	track_artist_display_name AS 'Artist',
	date_added AS 'Added'FROM
	track t
WHERE
	last_played IS NULL
AND
	NOT EXISTS
	(
		SELECT
			ratings_id
		FROM
			ratings r
		WHERE
			t.track_id = r.ratings_local_track_id

	)
ORDER BY
	Added DESC

====================================================================

SELECT
	count(*)	
FROM
	track t
INNER JOIN
	ratings r
ON
	t.track_id = r.ratings_local_track_id
WHERE
	t.in_library = 0
AND
	( t.play_count = 0 OR t.play_count IS NULL )
AND
	( r.ratings_value = 0 OR r.ratings_value IS NULL )
AND
	(julianday('now', 'localtime', 'start of day') - julianday(substr(t.date_added, 1, 4) || '-' || substr(t.date_added, 5, 2) || '-' || substr(t.date_added,7,2), 'localtime', 'start of day')) <= 30


SELECT
	count(*)	
FROM
	track t
WHERE
	t.in_library = 0
AND
	( t.play_count = 0 OR t.play_count IS NULL )
AND
	(julianday('now', 'localtime', 'start of day') - julianday(substr(t.date_added, 1, 4) || '-' || substr(t.date_added, 5, 2) || '-' || substr(t.date_added,7,2), 'localtime', 'start of day')) <= 30


UPDATE
	track
SET
	in_library = 1
WHERE
	in_library = 0
AND
	( play_count = 0 OR play_count IS NULL )
AND
	(julianday('now', 'localtime', 'start of day') - julianday(substr(date_added, 1, 4) || '-' || substr(date_added, 5, 2) || '-' || substr(date_added,7,2), 'localtime', 'start of day')) <= 30
