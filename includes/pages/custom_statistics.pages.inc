<?php
/**
 * @file
 * File containing pages rendering information.
 */

/**
 * Callback function for menu item on node page. Renders statistics table.
 */
function custom_statistics_render_statistics_callback($nid) {
  $items_on_page_count = 10;

  $conditions = array(
    'nid' => $nid,
    'pager_limit' => $items_on_page_count,
  );
  $temp = custom_statistics_get_user_views_information($conditions);

  $user_list = array();
  foreach ($temp as $user) {
    $username = $user['user']->name;
    if ($username == '') {
      $username = 'Guest';
    }
    else {
      $username = l($username, 'users/' . $username);
    }
    $user_list[] = array($username, $user['views']);
  }
  $table = array(
    'header' => array('User', 'Views'),
    'rows' => $user_list,
    'empty' => t('There is no available statistics for this node'),
  );

  return theme('table', $table) . theme('pager', array());
}
