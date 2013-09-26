--
-- SQL statements to be classified later.
--

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
