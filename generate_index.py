#!/usr/bin/env python3
import os
import glob
from collections import defaultdict


def generate_index_html():
    # Find all .html files in build directory (excluding index.html)
    html_files = glob.glob("build/**/*_wasm.html", recursive=True)

    # Group files by chapter
    chapters = defaultdict(list)
    for file_path in html_files:
        # Extract the relative path from build/
        rel_path = os.path.basename(file_path)
        if rel_path == "index.html":
            continue

        # Parse the filename to get chapter and example info
        name_parts = rel_path.replace("_wasm.html", "").split("_")
        if len(name_parts) >= 3:
            category = name_parts[0]  # examples or homework
            chapter = name_parts[1]
            example = "_".join(name_parts[2:])

            # Create a display name
            if category == "examples":
                display_name = f"Example {example}"
            else:
                display_name = f"Problem {example}"

            chapters[f"{category.title()} {chapter}"].append(
                {"path": rel_path, "name": display_name}
            )

    # Generate HTML content
    html_content = """<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>CS2602 WebAssembly Examples</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            line-height: 1.6;
            max-width: 1200px;
            margin: 0 auto;
            padding: 20px;
            background-color: #f5f5f5;
        }
        .container {
            background-color: white;
            padding: 30px;
            border-radius: 10px;
            box-shadow: 0 2px 5px rgba(0,0,0,0.1);
        }
        h1 {
            color: #2c3e50;
            text-align: center;
            margin-bottom: 30px;
        }
        h2 {
            color: #34495e;
            border-bottom: 2px solid #eee;
            padding-bottom: 10px;
            margin-top: 30px;
        }
        .chapter-grid {
            display: grid;
            grid-template-columns: repeat(auto-fill, minmax(250px, 1fr));
            gap: 20px;
            margin-top: 20px;
        }
        .example-card {
            background-color: #f8f9fa;
            border: 1px solid #dee2e6;
            border-radius: 5px;
            padding: 15px;
            transition: transform 0.2s, box-shadow 0.2s;
        }
        .example-card:hover {
            transform: translateY(-2px);
            box-shadow: 0 4px 8px rgba(0,0,0,0.1);
        }
        a {
            color: #3498db;
            text-decoration: none;
        }
        a:hover {
            color: #2980b9;
            text-decoration: underline;
        }
        .header {
            text-align: center;
            margin-bottom: 40px;
        }
        .description {
            color: #666;
            margin-bottom: 30px;
            text-align: center;
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="header">
            <h1>CS2602 WebAssembly Examples</h1>
            <div class="description">
                Interactive examples compiled to WebAssembly. Click on any example to try it out.
            </div>
        </div>
"""

    # Sort chapters to ensure consistent ordering
    for chapter in sorted(chapters.keys()):
        html_content += f"""
        <h2>{chapter}</h2>
        <div class="chapter-grid">"""

        # Sort examples within each chapter
        for example in sorted(chapters[chapter], key=lambda x: x["name"]):
            html_content += f"""
            <div class="example-card">
                <a href="{example['path']}">{example['name']}</a>
            </div>"""

        html_content += """
        </div>"""

    html_content += """
    </div>
</body>
</html>"""

    # Write the generated HTML to index.html in the build directory
    with open("build/index.html", "w") as f:
        f.write(html_content)


if __name__ == "__main__":
    generate_index_html()
