--
-- Get all songs in the library with their ratings.
--
.width 3 48 48
.output rated.txt
select r.ratings_value, t.track_name, t.artist_name
  from track t, ratings r
 where t.in_library <> 0
   and r.ratings_value > 0
   and t.track_id = r.ratings_local_track_id
 order by t.track_name asc, t.artist_name asc
;
.output stdout
