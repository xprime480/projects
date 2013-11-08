

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
;
