<table>
  <thead>
    <tr>
      <th><?php echo t('User')?></th>
      <th><?php echo t('Views')?></th>
    </tr>
  </thead>
  <tbody>
    <?php
      global $base_url;
      // TODO: retrieve nid from arguments.
      // Extracts nid from url.
      $nid = strval(explode('/', current_path())[1]);
      $user_list = custom_statistics_db_list_users($nid);
      foreach ($user_list as $item) {
        echo "<tr>\n";
        $username = $item['user']->name;
        if ($username == '') {
          $username = t('Guest');
          echo sprintf('<td>%s</td>', $username);
        }
        else
        {
          $user_profile_path = $base_url . '/users/' . $username;
          echo sprintf('<td><a href="%s">%s</a></td>', $user_profile_path, $username);
        }
        echo "\n";
        echo sprintf('<td>%s</td>', $item['views']);
        echo "\n";
        echo "</tr>\n";
      }
    ?>
  </tbody>
</table>
