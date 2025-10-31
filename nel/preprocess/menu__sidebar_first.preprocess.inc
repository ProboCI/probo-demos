<?php

/**
 * @file
 * Preprocess function for this hook.
 */

/**
 * Implements hook_preprocess_menu__REGION().
 *
 * This made possible by our custom theme suggestion.
 * @see uswds_theme_suggestions_menu_alter().
 */
function nel_preprocess_menu__sidebar_first(&$variables) {

  // if ($variables['attributes']['block'] == 'project_navigation') {
  //   // don't show first parent
  // }

  // Do we want to duplicate parent items as the first child?
  $variables['duplicate_parent'] = theme_get_setting('uswds_menu_accordion_duplicate_parent');

  if ($variables['duplicate_parent']) {
    $menu_link_manager = \Drupal::service('plugin.manager.menu.link');

    $node_id = \Drupal::routeMatch()->getRawParameter('node');
    if ($node_id) {
      $menu_links = $menu_link_manager->loadLinksByRoute('entity.node.canonical', array('node' => $node_id));
      if (is_array($menu_links) && count($menu_links)) {
        $menu_link = reset($menu_links);

        if ($menu_link->getParent()) {
          $parents = $menu_link_manager->getParentIds($menu_link->getParent());
          $parents = array_reverse($parents);
          $parent = reset($parents);
          $parent_menu_link = $menu_link_manager->createInstance($parent);
          $in_active_trail = false;
        } else {
          // We're on the root
          $parent_menu_link = $menu_link;
          $in_active_trail = true;
        }

        $title = $parent_menu_link->getTitle();
        $url = $parent_menu_link->getUrlObject()->toString();

        $variables['parent'] = [ // TODO: this is really the "root" not the "parent"
          'url' => $url,
          'title' => $title,
          'in_active_trail' => $in_active_trail,
        ];
      }
    }

  }
}
