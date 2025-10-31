<?php

use Drupal\node\NodeInterface;
use Drupal\node\Entity\NodeType;

function nel_preprocess_block__page_title_block(&$variables) {

  $variables['show_title'] = false;
  $node = \Drupal::routeMatch()->getParameter('node');
  if ($node instanceof NodeInterface) {
    $content_type = $node->getType();

    if ($node->hasField('field_show_title')) {
      $variables['show_title'] = $node->field_show_title->value ? true : false;
    }

    if (in_array($content_type, ['project_page', 'subcommittee'/*, 'review_question'*/])) {
      $variables['show_title'] = true;
    }

    // if ($content_type == 'systematic_review') {
    //   $variables['content']['#title'] = 'Overview';
    // }

  }

}
