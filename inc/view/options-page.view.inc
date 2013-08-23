<div class="wrap">
<?php screen_icon( 'options-general' ); ?>
<h2>OSU Welcome Dashboard Widget Options</h2>
<?php if ( isset( $_GET['updated'] ) ) : ?>
<div id="message" class="updated"><p><?php _e( 'Options saved.' ) ?></p></div>
<?php endif; ?>
<h3>Main Settings</h3>
<form method="post">
	<?php wp_nonce_field( 'osu_welcome_dashboard_widget_options' ); ?>
	<table class="form-table">
	<tr valign="top">
		<th scope="row"><label for="widget_content"><?php _e( 'Welcome Widget Content' ) ?></label></th>
		<td>
			<?php
				wp_editor(
					$widget_content,
					'widgetcontent',
					array(
						'textarea_name' => 'osu_welcome_dashboard_widget_options[widget_content]',
					)
				);
			?>
			This is the content for the Welcome dashboard widget.
		</td>
	</tr>
	</table>
</form>
</div>
