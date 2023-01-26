// For Node.js
var TurndownService = require("turndown");

// Import plugins from turndown-plugin-gfm
var turndownPluginGfm = require('turndown-plugin-gfm')
var gfm = turndownPluginGfm.gfm
var tables = turndownPluginGfm.tables
var strikethrough = turndownPluginGfm.strikethrough
 
var fs = require("fs");

var opts = require("@gerhobbelt/nomnom").parse();

var fp = opts[0]; // get the first positional arg
//var file = opts.file; // see if --file was specified
var verbose = opts.v; // see if -v was specified
var extras = opts._; // get an array of the unmatched, positional args


var turndownService = new TurndownService({
	headingStyle: 'atx',
	hr: '------',
	codeBlockStyle: 'fenced',
});
// Use the gfm plugin
turndownService.use(gfm)
 
// Use the table and strikethrough plugins only
//turndownService.use([tables, strikethrough])

function repeat (character, count) {
  return Array(count + 1).join(character)
}

if (0) {
// hack  the heading processing via the internals:
//console.log('rule:', turndownService.rules.options.rules.heading);
turndownService.rules.options.rules.heading.replacement = function (content, node, options) {
	// copy-pasta from the turndown source code, then patched to ensure the heading levels are bumped up:
    var hLevel = Number(node.nodeName.charAt(1)) + 1;

    return '\n\n' + repeat('#', hLevel) + ' ' + content + '\n\n'
};
}


console.log("fp:", fp);
var content = fs.readFileSync(fp, "utf8");

// hotfixes for the content, given that the HTML files are a little crufty:
content = content.replace(/<script[^]*?<\/script>/g, ' ');
content = content.replace(/<span>([\s\r\n]*)<\/span>/g, '$1');
content = content.replace(/<form[^]+?<\/form>/g, ' ');
content = content.replace(/<style[^]+?<\/style>/g, ' ');
content = content.replace(/<pre>/g, '<pre><code>');
content = content.replace(/<\/pre>/g, '</code></pre>');

content = content.replace(/<title[^]+?<\/title>/g, ' ');

var markdown = turndownService.turndown(content);

markdown = markdown.replace(/^\s*bibutils \/ Home \/ /, '# bibutils / ');

markdown = markdown.trim();

markdown = markdown.replace(/^[^]+?Authors:[^]+?#/, '#');

markdown = markdown.replace(/------$/, '');

markdown = markdown.trim() + '\n';


console.log("markdown:", markdown.length);

var mdf = fp.replace(".html", ".md");
fs.writeFileSync(mdf, markdown, "utf8");
