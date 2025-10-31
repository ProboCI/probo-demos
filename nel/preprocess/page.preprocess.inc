<?php

use Drupal\node\NodeInterface;
use Drupal\Core\Url;

/**
 * Implements hook_preprocess_page().
 */
function nel_preprocess_page(&$variables) {

  // Added to keep compatibility with the old uswds theme.
  $sidebar_first = (!empty($variables['page']['sidebar_first']));
  $sidebar_second = (!empty($variables['page']['sidebar_second']));
  if ($sidebar_first && $sidebar_second) {
    $variables['content_class'] = 'usa-width-one-half';
  }
  elseif ($sidebar_first || $sidebar_second) {
    $variables['content_class'] = 'usa-width-three-fourths';
  }
  else {
    $variables['content_class'] = 'usa-width-full';
  }
  $header_style = theme_get_setting('uswds_header_style');
  if (empty($header_style)) {
    $header_style = 'extended';
  }
  $variables['header_style'] = 'usa-header-' . $header_style;
  $variables['header_classes'] = 'usa-header ' . $variables['header_style'];

  $footer_style = theme_get_setting('uswds_footer_style');
  if (empty($footer_style)) {
    $footer_style = 'slim';
  }
  $variables['footer_style'] = 'usa-footer-' . $footer_style;
  $variables['footer_classes'] = 'usa-footer ' . $variables['footer_style'];

  // Set full_width variable for all put "page" content types. Pages use
  // paragraphs which handle the "usa-grid" classes themselves.

  // Site variables
  $site_config = \Drupal::config('system.site');
  $variables['site_name'] = $site_config->get('name');
  $variables['site_slogan'] = $site_config->get('slogan');
  $variables['site_logo'] = \Drupal::service('file_url_generator')->generateString(theme_get_setting('logo.url'));

  // Page variables
  $variables['full_width'] = false;
  $variables['page_subtitle'] = null;
  $variables['is_search'] = false;

  // Node
  $node = isset($variables['node']) ? $variables['node'] : null;
  if ($node instanceof NodeInterface) {
    $content_type = $node->getType();

    // Get view id

    // Full width, breadcrumbs, sidenav
    if (in_array($content_type, ['page', 'systematic_review'])) {
      // Set full_width variable for "page" content types. Pages use
      // paragraphs which handle the "usa-grid" classes themselves.
      $variables['full_width'] = true;
    }
    elseif (in_array($content_type, ['subcommittee', 'review_question', 'project_page'])) {
      $variables['show_breadcrumb'] = true;
      $variables['has_sidenav'] = true;
    }
    elseif (in_array($content_type, ['systematic_review_question_page', 'rapid_review', 'evidence_scan'])) {
      $variables['show_breadcrumb'] = true;
    }

    // Page subtitle
    if (
      $node->hasField('field_systematic_review')
      && $review_entity = $node->field_systematic_review->entity
    ) {
      $term_id = $review_entity->id();
      $subtitle = $review_entity->label();

      $variables['page_subtitle'] = $subtitle;

      // // Find the first node of content type "systematic_review" assigned to this
      // // taxonomy term. We'll use it's URL for the subtitle.
      // $nodes = \Drupal::entityTypeManager()->getStorage('node')->loadByProperties([
      //   'field_systematic_review' => $term_id,
      //   'type' => 'systematic_review',
      // ]);
      // if (is_array($nodes) && count($nodes)) {
      //   $systematic_review_node = reset($nodes);
      //   $url = Url::fromRoute('entity.node.canonical', ['node' => $systematic_review_node->id()])->toString();
      //   $variables['page_subtitle_url'] = $url;
      // }

    }

  }

  // // Footer settings from uswds 2.0.0
  // $variables['footer_menu_width'] = 'mobile-lg:grid-col-12';

  // // Some differences for the slim footer.
  // if ($variables['footer_slim']) {
  //   $variables['footer_menu_padding'] = 'desktop:padding-x-4';
  //   if ($variables['email'] || $variables['phone']) {
  //     $variables['footer_menu_width'] = 'mobile-lg:grid-col-8';
  //   }
  // }

  // Whether to display the primary footer section.
  $display_primary_footer = (!empty($variables['page']['footer']));
  $display_primary_footer |= (!empty($variables['page']['footer_menu']));
  $display_primary_footer |= ($variables['footer_slim'] && ($variables['email'] || $variables['phone']));
  $variables['display_footer_primary'] = $display_primary_footer;

  // Whether to display the secondary footer section.
  $display_secondary_footer = (!empty($variables['page']['footer_secondary']));
  $display_secondary_footer |= $variables['display_footer_agency'];
  $variables['display_footer_secondary'] = $display_secondary_footer;

  $footer_variables = [
    'footer_agency_name',
    'footer_agency_url',
    'footer_agency_logo',
    'contact_center',
    'phone',
    'email',
    'twitter',
    'facebook',
    'govdelivery',
    'instagram',
    'flickr',
    'youtube',
    'rss',
  ];
  foreach ($footer_variables as $footer_variable) {
    $variables[$footer_variable] = theme_get_setting('usda_' . $footer_variable);
  }

  // View
  $view_id = \Drupal::routeMatch()->getParameter('view_id');
  if ($view_id) {
    switch ($view_id) {
      case 'search_results':
        $variables['is_search'] = true;
        $variables['has_sidenav'] = true;

        $query = isset($_GET['query']) ? $_GET['query'] : null;
        $query = strip_tags($query);
        $variables['search_query'] = $query;

        break;
    }
  }
}
