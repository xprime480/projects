--
-- Remove rows from ratings that don't refer to tracks in the library.
--
delete from ratings
 where ratings_local_track_id not in
 		 (
		   select track_id
			  from track
		 )
;
