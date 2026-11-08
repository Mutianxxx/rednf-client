"""Shared optional diagnostics for live, configuration and legacy previews."""
from collections import Counter


CATEGORIES = ('unknown_structure', 'unknown_state', 'missing_resource',
              'resource_ambiguity', 'unconfirmed_geometry', 'runtime_evidence')


def issue(category, reason, **evidence):
    if category not in CATEGORIES:
        raise ValueError('Unknown preview diagnostic category: '+category)
    return dict(category=category, reason=reason, **evidence)


def diagnostics(issues, **details):
    issues = [dict(row, category=row.get('category', 'unknown_structure')) for row in issues]
    counts = Counter(row['category'] for row in issues)
    return dict(issues=issues, summary={key: counts[key] for key in CATEGORIES}, **details)
