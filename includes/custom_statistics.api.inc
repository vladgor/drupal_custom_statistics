<?php
/**
 * @file
 * Contains api functions.
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
  custom_statistics_db_insert_row($nid, $uid, $date);
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
  $tracked_node_types = variable_get('custom_statistics_tracked_node_types', array());
  foreach ($tracked_node_types as $tracked_type) {
    if ($tracked_type === $node_type) {
      return TRUE;
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
  $tracked_user_roles = variable_get('custom_statistics_tracked_user_roles', array());
  $is_tracked_user_role = count(array_intersect($tracked_user_roles, $user_roles));
  if ($is_tracked_user_role == 0) {
    return FALSE;
  }
  return TRUE;
}

/**
 * Get views count for given conditions.
 *
 * @param array $conditions
 *   Associative array with conditions for table items.
 *   Array items:
 *     int $nid - id of node,
 *     int $uid - id of user,
 *     DateTime $date_from - date from which function counts views, DateTime
 *     DateTime $date_to - date to which function counts views.
 */
function custom_statistics_get_views_count($conditions) {
  return custom_statistics_db_get_rows($conditions)->rowCount();
}

/**
 * Returns information about views count of certain node.
 *
 * @param array $conditions
 *   Associative array with conditions for table items.
 *   Array items:
 *     int $nid - id of node,
 *     DateTime $date_from - date from which function counts views, DateTime
 *     DateTime $date_to - date to which function counts views.
 *
 * @return array
 *   Returns array of associative arrays with following structure:
 *     'user' - user object (not uid or name!),
 *     'views' - views count.
 */
function custom_statistics_get_user_views_information($conditions) {
  $nid = NULL;
  $date_from = NULL;
  $date_to = NULL;
  if (!empty($conditions['nid'])) {
    $nid = $conditions['nid'];
  }
  if (!empty($conditions['date_from'])) {
    $date_from = $conditions['date_from'];
  }
  if (!empty($conditions['date_to'])) {
    $date_to = $conditions['date_to'];
  }

  $conditions['group_by'] = 'uid';
  $users = custom_statistics_db_get_rows($conditions);
  $user_list = [];
  foreach ($users as $item) {
    $count_conditions = array(
      'nid' => $nid,
      'uid' => $item->uid,
      'date_from' => $date_from,
      'date_to' => $date_to,
    );
    $user_list[] = array(
      'user' => user_load($item->uid),
      'views' => custom_statistics_get_views_count($count_conditions),
    );
  }

  return $user_list;
}
