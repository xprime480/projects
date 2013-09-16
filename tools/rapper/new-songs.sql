--
-- Get list of songs in june but not may database.
--
.width 48 48
.output new_in_june.txt
select a.track_name, a.artist_name
  from june.track a
 where a.rhapsody_id not in 
 		 (
		   select rhapsody_id
   		  from may.track
		 )
;
.output stdout
