--
-- Remove rows from ratings that don't refer to tracks in the library.
--
update tracks
set    in_library = 0
where  track_id in
		 (
		   select t.track_id
           from tracks t
          where t.in_library = 1
            and t.play_count > 0
            and ( t.track_id not in
                  (
						  select r.ratings_local_track_id
 						    from ratings r
					   )
						or
						t.track_id in
						(
						  select r.ratings_local_track_id
						    from ratings r,
							      tracks t
						   where t.track_id = r.ratings_local_track_id
                       and r.ratings_value <= 0
						)
					 )
		 )
;
     
--delete from ratings
-- where ratings_local_track_id not in
-- 		 (
--		   select track_id
--			  from track
--		 )
--;
