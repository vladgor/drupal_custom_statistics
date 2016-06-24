<?php
/**
 * @file
 * Contains custom functions.
 */

/**
 * Registers hit of the certain node by certain user.
 *
 * @param int $nid
 *   Id of visited node.
 * @param int $uid
 *   Id of tracked user.
 * @param DateTime $date
 *   (optional) Date of visiting. If omitted function will use current date and
 *   time.
 */
function custom_statistics_register_hit($nid, $uid, DateTime $date = NULL) {
  if (is_null($date)) {
    $date = new DateTime();
  }
  custom_statistics_db_insert_row($nid, $uid, $date->getTimestamp());
}

/**
 * Checks if node type is tracked.
 *
 * @param string $node_type
 *   Name of node type to be checked.
 *
 * @return bool
 *   Returns TRUE if node belongs to tracked node types. Otherwise returns
 *   FALSE.
 */
function custom_statistics_is_node_type_tracked($node_type) {
  $node_type = strtolower($node_type);
  $tracked_node_types = variable_get('custom_statistics_tracked_node_types');
  if (isset($tracked_node_types)) {
    foreach ($tracked_node_types as $tracked_type) {
      if ($tracked_type === $node_type) {
        return TRUE;
      }
    }
  }
  return FALSE;
}

/**
 * Checks if user's role is tracked.
 *
 * @param array $user_roles
 *   Array of user roles.
 *
 * @return bool
 *   Returns TRUE if user belongs to tracked roles. Otherwise returns FALSE.
 */
function custom_statistics_is_user_role_tracked($user_roles) {
  $tracked_user_roles = variable_get('custom_statistics_tracked_user_roles');
  if (!isset($tracked_user_roles)) {
    return FALSE;
  }
  $is_tracked_user_role = count(array_intersect($tracked_user_roles, $user_roles));
  if ($is_tracked_user_role == 0) {
    return FALSE;
  }
  return TRUE;
}

/**
 * Returns rendered table with view statistics from template.
 *
 * @param int $nid
 *   Id of node which function is rendering statistics table for.
 *
 * @return string
 *   Returns string with rendered table with information about views of
 *   specified node. If there is no information available, returns notifying
 *   string.
 */
function custom_statistics_render_statistics_table($nid) {
  global $base_url;
  $temp = custom_statistics_db_list_users($nid);
  if (empty($temp)) {
    return t('There is no views information available for this node.');
  }

  $user_list = array();
  foreach ($temp as $user) {
    $username = $user['user']->name;
    if ($username == '') {
      $username = 'Guest';
    }
    else {
      $userlink = $base_url . '/users/' . $username;
      $username = sprintf('<a href="%s">%s</a>', $userlink, $username);
    }
    $user_list[] = array($username, $user['views']);
  }
  $table = array(
    'header' => array('User', 'Views'),
    'rows' => $user_list,
  );

  return theme('table', $table);
}
