
.output new_playlist.txt

.width 25 25 7 7

--
-- CREATE THE FIRST AUTO-PLAYLIST, old 4 and 5 star rated songs
--

SELECT t.artist as Artist, t.track as Track, 
		 r.ratings_value as Rating, t.count as Count
  FROM (
         SELECT track_id, last_played, track_artist_display_name as artist,
			       track_name as track, play_count as count,
					 julianday('now', 'start of day') - julianday(substr(last_played, 1, 4) || '-' || substr(last_played, 5, 2) || '-' || substr(last_played,7,2), 'start of day') as days,
					 abs(RANDOM() % 10000 / 100.0) as JITTER
		     FROM track
			 WHERE in_library = 1
	    ) t
 INNER JOIN ratings r
    ON t.track_id = r.ratings_local_track_id
 WHERE ( r.ratings_value = 5 AND t.days > 0 )
    OR ( r.ratings_value = 4 AND t.days > 6 )
--ORDER BY t.last_played DESC
 ORDER BY t.jitter
;

.output stdout
