<?php

function nel_preprocess_views_view__search_results(&$variables) {
  // Search query
  $query = isset($_GET['query']) ? $_GET['query'] : '';
  $query = strip_tags($query);
  $variables['search_query'] = $query;
}
