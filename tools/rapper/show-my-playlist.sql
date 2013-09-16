--
-- Show the current contents of the dynamic playlist.
--
SELECT
	pt.sequence as NUMBER,
	t.TRACK_ARTIST_DISPLAY_NAME as ARTIST,
	t.TRACK_NAME as TRACK
FROM
	track t
INNER JOIN
	playlist_track pt
ON
	t.track_id = pt.track_id
INNER JOIN
	playlist p
ON
	p.playlist_id = pt.playlist_id
WHERE
	p.playlist_name LIKE 'My Dynamic%'
ORDER BY
	pt.sequence ASC
;
