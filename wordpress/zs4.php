<?php
 
/*
 
* Plugin Name: zs4
 
* Description: This plugin allows for complex json objects to be managed
 
* Version: 1.0
 
* Author: count inn
 
* Author URI: http://zs4.org
 
*/

/**********************************
 *  support ajax interaction
 */
 
add_action( 'wp_ajax_zs4', 'zs4' );

function zs4() {
	die( "Hello World" );
}



/**********************************
 *  use the zs4.js javascript library
 */
 
wp_enqueue_script('zs4', plugins_url('/zs4.js',__FILE__) );
wp_enqueue_script('zs4-wordpress', plugins_url('/zs4-wordpress.js',__FILE__) );
wp_enqueue_style( 'zs4', plugins_url('/zs4/zs4.css') );

/**********************************
 *  Here's the zs4 post type
 */
add_action( 'init', 'zs4_create_post_types' );

function zs4_create_post_types(){
	    register_post_type( 'zs4',
        array(
            'labels' => array(
                'name' => 'zs4',
                'singular_name' => 'zs4',
                'add_new' => 'Add New',
                'add_new_item' => 'Add New zs4',
                'edit' => 'Edit',
                'edit_item' => 'Edit zs4',
                'new_item' => 'New zs4',
                'view' => 'View',
                'view_item' => 'View zs4',
                'search_items' => 'Search zs4',
                'not_found' => 'No zs4 found',
                'not_found_in_trash' => 'No zs4 found in Trash',
                'parent' => 'Parent zs4'
            ),
 
            'public' => true,
            'menu_position' => 15,
            'supports' => array( 'title', 'editor'),
            'taxonomies' => array( 'song','js','json' ),
            //'menu_icon' => plugins_url( 'images/image.png', __FILE__ ),
            'has_archive' => true
        )
    );
}

/**********************************
 *  Here's the zs4 shortcode
 */
$zs4_object_id = 0; // global scope
 
function zs4_function($atts, $content = null){
	global $zs4_object_id;
	$zs4_object_id++;
	
	$ret  = "<div id='zs4_" . $zs4_object_id . "'></div>";
	$ret .= "<script type='text/javascript'>";
	$ret .= "zs4.html.init.id('zs4_" . $zs4_object_id . "');";
	if ($content!=null){
		$ret .= ("zs4.zs4.data = " . json_encode(utf8_encode($content)) . ";");
	}

	foreach ($atts as $key => $value) {
		$ret .= "zs4.zs4.arg." . $key . "= " . json_encode(utf8_encode($value)) . ";";
	}
	
	$ret .= "zs4.zs4.run();";
	$ret .= "</script>";
	
	return $ret;
}
 
add_shortcode('zs4', 'zs4_function');

?>