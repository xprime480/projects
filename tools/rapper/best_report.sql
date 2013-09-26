
.output best_report.txt

.width 25 25 7 7 7 

SELECT 
	t.TRACK_ARTIST_DISPLAY_NAME as ARTIST,
	t.TRACK_NAME as TRACK,
	r.RATINGS_VALUE as RATING,
	t.PLAY_COUNT as COUNT,
	julianday('now', 'start of day') - julianday(substr(t. LAST_PLAYED, 1, 4) || '-' || substr(t.LAST_PLAYED, 5, 2) || '-' || substr(t.LAST_PLAYED,7,2), 'start of day') as DAYS
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
;

.output stdout
