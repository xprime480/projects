.mode csv
.output playdates.txt

select playdate, count(*) as number
  from (
			select substr(last_played, 0, 9) as playdate
			  from track
			 where in_library = 1
           
 		 )
 where playdate is not NULL
 group by playdate
 order by playdate desc
;

.mode column
.output stdout
