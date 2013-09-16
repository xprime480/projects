--
-- Select never played songs.
--

.width 48 20
.output unheard.txt
select track_name, date_added
  from track
 where play_count is null
 order by date_added desc
 limit 100
;
.output stdout
