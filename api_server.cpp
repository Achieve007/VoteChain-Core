// api_server.cpp
// REST API Server for Blockchain Voting System
// Run: ./api_server
// Test: curl -X POST http://localhost:8080/addVote -H "Content-Type: application/json" -d '{"voterTempID":"VOTER-001","candidate":"Alice"}'

#include "VotingAPI.h"
#include "Blockchain.h"
#include <crow.h>
#include <iostream>

int main() {
    // Initialize blockchain
    Blockchain votingChain;
    
    // Initialize API
    VotingAPI api(votingChain);
    
    // Create Crow app
    crow::SimpleApp app;
    
    std::cout << "\n╔══════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║       Blockchain Voting System - REST API Server        ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════════╝\n" << std::endl;
    
    // ============================================================
    // POST /addVote - Submit a vote
    // ============================================================
    CROW_ROUTE(app, "/addVote")
        .methods("POST"_method)
        ([&api](const crow::request& req) {
            return api.handleAddVote(req);
        });
    
    // ============================================================
    // GET /stats - Get voting statistics
    // ============================================================
    CROW_ROUTE(app, "/stats")
        .methods("GET"_method)
        ([&api](const crow::request& req) {
            return api.handleGetStats(req);
        });
    
    // ============================================================
    // GET /block/:index - Get specific block
    // ============================================================
    CROW_ROUTE(app, "/block/<int>")
        .methods("GET"_method)
        ([&api](const crow::request& req, int blockIndex) {
            return api.handleGetBlock(req, blockIndex);
        });
    
    // ============================================================
    // GET /deadblock - Get rejected votes
    // ============================================================
    CROW_ROUTE(app, "/deadblock")
        .methods("GET"_method)
        ([&api](const crow::request& req) {
            return api.handleGetDeadBlock(req);
        });
    
    // ============================================================
    // GET /validate - Validate blockchain integrity
    // ============================================================
    CROW_ROUTE(app, "/validate")
        .methods("GET"_method)
        ([&api](const crow::request& req) {
            return api.handleValidateChain(req);
        });
    
    // ============================================================
    // GET / - API Documentation
    // ============================================================
    CROW_ROUTE(app, "/")
        ([](const crow::request& req) {
            crow::json::wvalue response;
            response["name"] = "Blockchain Voting System API";
            response["version"] = "1.0.0";
            response["endpoints"] = crow::json::wvalue::list({
                crow::json::wvalue{
                    {"method", "POST"},
                    {"path", "/addVote"},
                    {"description", "Submit a vote to the blockchain"}
                },
                crow::json::wvalue{
                    {"method", "GET"},
                    {"path", "/stats"},
                    {"description", "Get voting statistics"}
                },
                crow::json::wvalue{
                    {"method", "GET"},
                    {"path", "/block/:index"},
                    {"description", "Get specific block by index"}
                },
                crow::json::wvalue{
                    {"method", "GET"},
                    {"path", "/deadblock"},
                    {"description", "Get rejected votes"}
                },
                crow::json::wvalue{
                    {"method", "GET"},
                    {"path", "/validate"},
                    {"description", "Validate blockchain integrity"}
                }
            });
            return response;
        });
    
    // Start server
    std::cout << "🚀 Server starting on http://localhost:8080" << std::endl;
    std::cout << "📝 API Documentation: http://localhost:8080/" << std::endl;
    std::cout << "📊 Statistics: http://localhost:8080/stats" << std::endl;
    std::cout << "\n⚡ Ready to accept votes!\n" << std::endl;
    
    app.port(8080)
       .multithreaded()
       .run();
    
    return 0;
}