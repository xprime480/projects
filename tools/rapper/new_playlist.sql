
--.output temp.txt

select max(playlist_id), 1 + max(playlist_id) as new
  from playlist
;

insert into playlist
       (
		   playlist_id,
			playlist_name,
			playlist_type,
			sync_state,
			last_guid_used
		 )
select 1 + max(playlist_id),
		 'Test Playlist',
		 0,
		 0,
		 0
  from playlist
;

insert into playlist_track
select max(playlist_id),
		 24542,
		 1,
		 1
  from playlist
;

select playlist_id, count(*)
  from playlist_track
 group by playlist_id
;


--.output stdout
