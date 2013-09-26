
.output added-not-recently.txt

.width 25 25 16

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
;

.output stdout
